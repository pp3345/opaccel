--TEST--
strlen() with VAR argument
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	echo strlen(count(range(0, 100)));

?>
--EXPECT--
3