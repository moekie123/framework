<?php
	$tests = scandir('/opt/framework/gtest/');

	foreach ($tests as $test) 
	{
		if( is_executable( '/opt/framework/gtest/'.$test ))
		{
			$output = NULL;

			exec('/opt/framework/gtest/'.$test.' 2>&1', $output);

			if ( strpos( $output[0], 'Permission denied' ) !== false ) 		
				continue;

			//var_dump( $output );
?>

<div class="unittest" style="margin-top:50px">

<h1 class="unittest-header"> Unit test [<?php echo "$test"; ?>] </h1>

<pre class="unittest-result">
<?php
			foreach ( $output as $line )
			{
				if ( !(strpos( $line, 'Permission' ) !== false) ) 
					echo "$line\n";
			}
		?>
</pre>
</div>
		<?php

		}
	}
?>


