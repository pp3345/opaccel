--TEST--
strlen() with resource argument
--INI--
opaccel.optimizations=1
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	$a = fopen("/dev/urandom", "r");
	echo strlen($a);

?>
--EXPECTF--

Warning: strlen() expects parameter 1 to be string, resource given in %s on line %d