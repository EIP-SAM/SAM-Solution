<?php

define("TEST_DIR_NAME", "Tests");
define("PRO_FILE_NAME", "Tests.pro");
define("BIN_TEST_NAME", "Tests");

$root = 'source';
$startPath = getcwd();

$iter = new RecursiveIteratorIterator(
    new RecursiveDirectoryIterator($root, RecursiveDirectoryIterator::SKIP_DOTS),
        RecursiveIteratorIterator::SELF_FIRST,
	    RecursiveIteratorIterator::CATCH_GET_CHILD // Ignore "Permission denied"
	    );

$paths = array();
foreach ($iter as $path => $dir) {
    if ($dir->isDir() && $dir->getFileName() == TEST_DIR_NAME) {
        $paths[realpath($dir->getPathName())] = getDirContents($path);
    }
}

foreach ($paths as $path => $content) {
    $retval = -1;
    if (!in_array(PRO_FILE_NAME, $content)){
        echo getColoredString("No " . PRO_FILE_NAME . " found in folder " . $path . PHP_EOL, 'yellow');
        continue;
    }
    chdir($path);
    system('qmake ' . PRO_FILE_NAME, $retval);
    if ($retval == 0) {
        ob_start();
        $lastLine = system('make', $retval);
        ob_end_clean();
        if ($retval == 0) {
            system('./' . BIN_TEST_NAME, $retval);
            if ($retval == 0) {
                echo getColoredString("Tests OK" . PHP_EOL, 'green');
            } else {
                echo getColoredString("Tests error in" . $path . PHP_EOL, 'red');
            }
        } else {
            echo getColoredString("Error when compiling with Makefile in folder " . $path . PHP_EOL, 'yellow');
        }
    } else {
        echo getColoredString("Error when compiling " . PRO_FILE_NAME . " in folder " . $path . PHP_EOL, 'yellow');
    }
    chdir($startPath);
}

function getColoredString($string, $color) {
    $colors = array(
        'red' => '41',
        'green' => '42',
        'cyan' => '46',
        'yellow' => '43',
    );

    $colored_string = "\033[" . $colors[$color] . "m";

    $colored_string .=  $string . "\033[0m";

    return $colored_string;
}

function getDirContents($dir, &$results = array()){
    $files = scandir($dir);

    foreach($files as $key => $value){
        $path = realpath($dir.DIRECTORY_SEPARATOR.$value);
        if(!is_dir($path)) {
            $results[] = $value;
        } else if(is_dir($path) && $value != "." && $value != "..") {
            getDirContents($path, $results);
            $results[] = $value;
        }
    }

    return $results;
}

?>