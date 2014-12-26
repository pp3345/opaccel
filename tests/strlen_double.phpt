--TEST--
strlen() with float argument
--INI--
opaccel.optimizations=1
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	$a = 12.345;
	echo strlen($a);

?>
--EXPECT--
6