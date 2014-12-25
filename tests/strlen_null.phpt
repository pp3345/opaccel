--TEST--
strlen() with NULL argument
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