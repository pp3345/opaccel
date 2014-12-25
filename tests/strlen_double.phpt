--TEST--
strlen() with float argument
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