<?php
	
	$commands = array(
			"cd /var/www/csci222.com/",
			"sudo git pull git@github.com:asjadathick/BitQA-Dev.git",
			"cd /var/www/csci222.com/BitQA",
			"sudo make build"
		);

	foreach ($commands as $command) {
		$output = shell_exec($command);
		echo "<p>$ {$command} <br>" . $output . "<br></p>";
	};
