--TEST--
strlen() with VAR argument
--INI--
opaccel.optimizations=1
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	echo strlen(count(range(0, 100)));

?>
--EXPECT--
3