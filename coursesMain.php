<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<link rel="stylesheet" href="styles.css" type="text/css">
	<title>RGU CSDM</title>
</head>
<body>
	<script>
	var acc = document.getElementsByClassName("accordion");
	var i;

	for (i = 0; i < acc.length; i++) {
		acc[i].onclick = function(){
			this.classList.toggle("active");
			this.nextElementSibling.classList.toggle("show");
	  }
	}
	</script>
	<div class="wrapper">
	
		<div id="header">
			<?php include_once('header.php'); ?>
		</div>
		
		<div id="content">
			<h2 style="padding-left:7.5%;"> HEADING TITLE </h2>
			<hr style="margin-top:4px;">
			<div class="contentLeft">
				<button class="accordion"> Undergraduate </button>
				<div class="panel">
				<p>Lorem Ipsum...</p>
					<button class="accordion"> COURSE1 </button>
					<div class="panel">
						<p>Lorem Ipsum...</p>
					</div>
					<button class="accordion"> COURSE2 </button>
					<div class="panel">
						<p>Lorem Ipsum...</p>
					</div>
					<button class="accordion"> COURSE3 </button>
					<div class="panel">
						<p>Lorem Ipsum...</p>
					</div>
				</div>
				<button class="accordion"> Postgraduate </button>
				<div class="panel">
					<button class="accordion"> COURSE1 </button>
					<div class="panel">
						<p>Lorem Ipsum...</p>
					</div>
					<button class="accordion"> COURSE2 </button>
					<div class="panel">
						<p>Lorem Ipsum...</p>
					</div>
					<button class="accordion"> COURSE3 </button>
					<div class="panel">
						<p>Lorem Ipsum...</p>
					</div>
				</div>
			</div>
			
			<div class="contentRight">
				<?php include_once('sidebar.php'); ?>
			</div>
		</div>
			
		<div id="footer">
			<?php include_once('footer.php'); ?>
		</div>
	</div>
</body>
</html>
