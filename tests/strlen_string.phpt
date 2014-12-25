--TEST--
strlen() with string argument
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	$a = "abcdef";
	echo strlen($a);

?>
--EXPECT--
6