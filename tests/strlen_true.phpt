--TEST--
strlen() with bool(true) argument
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