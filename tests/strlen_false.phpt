--TEST--
strlen() with bool(false) argument
--INI--
opaccel.optimizations=1
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	$a = false;
	echo strlen($a);

?>
--EXPECT--
0