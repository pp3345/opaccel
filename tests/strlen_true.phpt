--TEST--
strlen() with bool(true) argument
--INI--
opaccel.optimizations=1
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	$a = true;
	echo strlen($a);

?>
--EXPECT--
1