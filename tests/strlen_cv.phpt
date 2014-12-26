--TEST--
strlen() with CV argument
--INI--
opaccel.optimizations=1
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	$a = 7.123;
	
	echo strlen($a);

?>
--EXPECT--
5