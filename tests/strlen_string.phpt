--TEST--
strlen() with string argument
--INI--
opaccel.optimizations=1
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