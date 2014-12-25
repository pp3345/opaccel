--TEST--
strlen() with integer argument
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	$a = 123456789;
	echo strlen($a);

?>
--EXPECT--
9