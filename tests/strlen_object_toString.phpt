--TEST--
strlen() with object (with __toString()) argument
--SKIPIF--
<?php require_once 'skipif.inc';
?>
--FILE--
<?php

	class Test {
		public function __toString() {
			return "abcdefghi";
		}
	}

	$a = new Test;
	echo strlen($a);

?>
--EXPECT--
9