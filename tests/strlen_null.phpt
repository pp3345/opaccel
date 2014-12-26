--TEST--
strlen() with NULL argument
--INI--
opaccel.optimizations=1
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	$a = null;
	echo strlen($a);

?>
--EXPECT--
0