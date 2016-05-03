<?php
	
	$commands = array(
			"sudo -Hu www-data git -C /var/www/csci222.com/ reset --hard HEAD 2>&1",
			"sudo -Hu www-data git -C /var/www/csci222.com/ pull git@github.com:asjadathick/BitQA-Dev.git 2>&1",
			"make -C /var/www/csci222.com/BitQA build 2>&1"
		);

	foreach ($commands as $command) {
		$output = shell_exec($command);
		echo "<p>$ {$command} <br> {$output}<br></p>";
	};
