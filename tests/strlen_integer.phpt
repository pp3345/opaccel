--TEST--
strlen() with integer argument
--INI--
opaccel.optimizations=1
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	$a = 123456789;
	echo strlen($a);

?>
--EXPECT--
9