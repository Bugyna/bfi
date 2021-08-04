<?php
	function interpret($text, $input=null)
	{
		$text = str_split($text);
		if (!empty($input)) { $input = str_split($input); }
		$cells = [0];
		$ptr = 0;
		$input_ptr = 0;

		$loops = [];
		$loop_ptr = 0;

		$i = 0;
		
		while ($i < count($text)-1) {
			$c = $text[$i];

			switch ($c) {
			case "+":
				$cells[$ptr]++;
				if ($cells[$ptr] > 255) {
					$cells[$ptr] = 0;
				}
				break;

			case "-":
				$cells[$ptr]--;
				if ($cells[$ptr] < 0) {
					$cells[$ptr] = 255;
				}
				break;

			case ">":
				$ptr++;
				if (!isset($cells[$ptr])) {
					$cells[$ptr] = 0;
				}
				break;

			case "<":
				$ptr--;
				if ($ptr < 0) { echo "error"; }
				break;

			case ".":
				echo chr($cells[$ptr]);
				break;

			case ",":
				echo $input[$input_ptr++];
				break;

			case "[":
				if (!isset($loops[$loop_ptr])) {
					$loops[$loop_ptr] = 0;
				}
				$loops[$loop_ptr] = $i;
				$loop_ptr++;
				break;

			case "]":
				$loop_ptr--;
				if ($cells[$ptr] !== 0) {
					$i = $loops[$loop_ptr];
					$loop_ptr++;
				}
				break;
			}
			
			$i++;
		}
	}
?>
<!DOCTYPE HTML>
<html lang="en">
</head>
	<title> placeholder </title>
	<link rel="stylesheet" href="main.css">
<head>

<body>
	<form method="POST">
		<textarea name="text"></textarea>
		<textarea name="input"></textarea>
		<button name="submit"> run </button>
	</form>
	
	<?php
		if (isset($_POST["submit"])) {
			interpret($_POST["text"], $_POST["input"]);
		}
	?>
</body>
</html>