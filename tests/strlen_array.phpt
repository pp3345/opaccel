--TEST--
strlen() with array argument
--INI--
opaccel.optimizations=1
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	$a = [1, 2, 3];
	echo strlen($a);

?>
--EXPECTF--

Warning: strlen() expects parameter 1 to be string, array given in %s on line %d