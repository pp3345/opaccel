--TEST--
strlen() with array argument
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