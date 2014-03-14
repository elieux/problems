<?php

$utf8text = file_get_contents('l2-2.txt');
$koi8text = iconv('UTF-8', 'KOI8-R', $utf8text);
$koi8textstripped = '';
for ($i = 0; $i < strlen($koi8text); $i++)
{
	$codepoint = ord(substr($koi8text, $i, 1));
	if ($codepoint >= 32)
		// $codepoint &= 0x7f;
		$codepoint -= 30;
	$koi8textstripped .= chr($codepoint);
}

$utf8text = file_get_contents('l2-2.txt');
$iso88595text = iconv('UTF-8', 'ISO-8859-5', $utf8text);
$iso88595textstripped = '';
for ($i = 0; $i < strlen($iso88595text); $i++)
{
	$codepoint = ord(substr($iso88595text, $i, 1));
	if ($codepoint >= 32)
		// $codepoint &= 0x7f;
		$codepoint += 33;
	$iso88595textstripped .= chr($codepoint);
}

// $utf8textstripped = iconv('KOI8-R', 'UTF-8', $koi8textstripped);
// $utf8textstripped = iconv('ISO-8859-5', 'UTF-8', $iso88595textstripped);

$tr = array(
	'с' => 'У',
	
	'н' => 'О',
	
	'м' => 'н',
	
	'П' => 'р',
	'Н' => 'о',
	'Б' => 'в',
	'Е' => 'е',
	'М' => 'н',
	'Э' => 'ь',
	
	'Р' => 'т',
	'Х' => 'и',
	
	'Я' => 'с',
	'Ю' => 'а',
	'Ж' => 'ц',
	'Й' => 'к',
	'Д' => 'д',
	'Ш' => 'ы',
	'я' => 'с',
	'Л' => 'м',
	
	'Ф' => 'ж',
	
	'О' => 'п',
	'К' => 'л',
	
	'╧' => '№',
	
	'С' => 'у',
);
$utf8textstripped = str_replace(array_keys($tr), array_values($tr), $utf8text);

echo $utf8textstripped;
