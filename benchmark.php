<?php

	echo "Zend Opcache enabled: " . (extension_loaded("Zend OPCache") && ini_get("opcache.enable_cli") ? "yes" : "no") . PHP_EOL;
	echo "Opaccel enabled: " . (in_array("opaccel", get_loaded_extensions(true)) ? "yes" : "no") . PHP_EOL;
	echo PHP_EOL;
	
	function Benchmark($name, callable $call) {
		global $results;
		
		echo "Benchmarking $name..." . PHP_EOL;
		
		$start = microtime(true);
		$call();
		
		$results[$name] = microtime(true) - $start;
	}
		
	Benchmark("10M iterations of strlen()", function() {
		$a = "abc";
		
		for($i = 0; $i < 10000000; $i++) {
			$x = strlen($a);
		}
	});
	
	echo "All tests completed" . PHP_EOL;
	echo PHP_EOL;
	echo "Results" . PHP_EOL;
	echo "===================" . PHP_EOL;
	
	$totalTime = 0;
	
	foreach($results as $name => $time) {
		echo "$name: $time seconds" . PHP_EOL;
		$totalTime += $time;
	}
	
	echo "Total time: $time seconds" . PHP_EOL;
