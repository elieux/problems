<?php

$start = 1;
$stop = 20;

function test($k, $m) {
	$people = array_fill(1, $k * 2, true);
	$people = array_combine(array_keys($people), array_keys($people));
	
	$deadKey = 0;
	do {
		$keys = array_keys($people);
		$deadKey = ($deadKey + $m - 1) % count($keys);
		$deadMan = $keys[$deadKey];
		
		if (1 <= $deadMan && $deadMan <= $k)
			return false;
		
		$people[$deadMan] = null;
		$people = array_filter($people);
	} while ($k < count($people));
	return true;
}

function main2($k) {
	for ($n = 2 * $k, $m = 2;; $m++) {
	  for ($p = 0, $r = $n; $r > $k; $r--)
		 if (($p = ($p + $m - 1) % $r) < $k) break;
	  if ($r == $k) return $m;
	}
}

function main($k) {
	$mi = 0;
	do {
		for ($m = (1 + 2 * $mi) * $k + 1; (2 + 2 * $mi) * $k >= $m; $m += 1) {
			$hasSucceeded = test($k, $m);
			if ($hasSucceeded)
				break 2;
		}
		$mi += 1;
	} while (true);
	return $m;
}

for ($k = $start; $stop >= $k; $k += 1) {
	echo sprintf("k = %3d, m = %3d\n", $k, main2($k));
}
