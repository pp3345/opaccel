--TEST--
strlen() with TMP_VAR argument
--INI--
opaccel.optimizations=1
--SKIPIF--
<?php require_once 'skipif.inc';?>
--FILE--
<?php
	
	$a = 7;
	
	echo strlen($a + 5);

?>
--EXPECTF--
2