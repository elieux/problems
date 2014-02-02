<?php

// 323 = 17 x 19
// 17 + 19 = 36
echo base_convert((int)base_convert('begad', 17, 10) + (int)base_convert('gif', 19, 10), 10, 36);
echo PHP_EOL;
echo base_convert((int)base_convert('begad', 19, 10) + (int)base_convert('gif', 17, 10), 10, 36);
echo PHP_EOL;
