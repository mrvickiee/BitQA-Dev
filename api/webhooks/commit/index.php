<?php
	
	$commands = array(
			"cd /var/www/csci222.com/ 2>&1",
			"git pull git@github.com:asjadathick/BitQA-Dev.git 2>&1",
			"cd /var/www/csci222.com/BitQA 2>&1",
			"sudo make build 2>&1"
		);

	foreach ($commands as $command) {
		$output = shell_exec($command);
		echo "<p>$ {$command} <br>" . $output . "<br></p>";
	};
