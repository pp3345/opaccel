--TEST--
strlen() with object argument
--INI--
opaccel.optimizations=1
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	$a = new stdClass;
	echo strlen($a);

?>
--EXPECTF--

Warning: strlen() expects parameter 1 to be string, object given in %s on line %d