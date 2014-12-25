--TEST--
strlen() with bool(false) argument
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