// Array with all the images. 
var imgs = new Array(9);

imgs[0] = new Image(); // create new instance of image object
imgs[0].name = "Armory";
imgs[0].src = "armory.jpg"; //set image object src property to an image's src, preloading that image in the process
imgs[0].year = "1896";
imgs[0].arch = "Charles Aldrich";
imgs[0].description = "Built for athletics and military drill, as well as performing arts and social activities. Memorial plaques at the front entrance honor students, faculty, and alumni who fought in the Spanish-American War.";

imgs[1] = new Image(); 
imgs[1].name = "Eddy Hall";
imgs[1].src = "eddy.jpg"; 
imgs[1].year = "1886";
imgs[1].arch = "LeRoy Buffington";
imgs[1].description = "Built as Mechanic Arts. It is the oldest existing building on campus. Named for Henry Turner Eddy, professor of engineering and mathematics and dean of the Graduate School.";

imgs[2] = new Image(); 
imgs[2].name = "Folwell";
imgs[2].src = "folwell.jpg"; 
imgs[2].year = "1907";
imgs[2].arch = "Clarence H. Johnston, Sr.";
imgs[2].description = "When Old Main burned in 1904, Folwell Hall was built to house displaced departments. Named for William Watts Folwell, first president of the University, 1869-84.";

imgs[3] = new Image(); 
imgs[3].name = "Jones";
imgs[3].src = "jones.jpg"; 
imgs[3].year = "1901";
imgs[3].arch = "Charles Aldrich";
imgs[3].description = "Built as Physics Building. Named for Frederick S. Jones, professor of physics and dean of the College of Engineering.";

imgs[4] = new Image(); 
imgs[4].name = "Music Education";
imgs[4].src = "music.jpg"; 
imgs[4].year = "1888";
imgs[4].arch = "Warren H. Hayes";
imgs[4].description = "Built as Student Christian Association building. Acquired by the University, it housed Child Welfare and Music Education.";

imgs[5] = new Image(); 
imgs[5].name = "Nicholson";
imgs[5].src = "nicholson.jpg"; 
imgs[5].year = "1890";
imgs[5].arch = "LeRoy Buffington with Harvey Ellis";
imgs[5].description = "Built as chemical laboratory. In 1914, chemistry moved to the mall area and Nicholson was remodeled for the men's union until Coffman Memorial Union was built as a coed student union. Named for Edward E. Nicholson, professor of chemistry and later dean of Student Affairs.";

imgs[6] = new Image(); 
imgs[6].name = "Pillsbury";
imgs[6].src = "pillsbury.jpg"; 
imgs[6].year = "1889";
imgs[6].arch = "Leroy Buffington with Harvey Ellis";
imgs[6].description = "Built as Science Hall. Named for Governor John S. Pillsbury.";

imgs[7] = new Image(); 
imgs[7].name = "Pillsbury Statue";
imgs[7].src = "statue.jpg"; 
imgs[7].year = "1900";
imgs[7].arch = "Daniel C. French, sculptor";
imgs[7].description = "Pillsbury statue located across the street from Burton Hall.";

imgs[8] = new Image(); 
imgs[8].name = "Wesbrook";
imgs[8].src = "wesbrook.jpg"; 
imgs[8].year = "1898";
imgs[8].arch = "rederick Corser";
imgs[8].description = "Built as Laboratory of Medical Science. In 1912, dentistry moved here. Named for Frank Wesbrook, professor of pathology and bacteriology and dean of the College of Medicine and Surgery.";

imgs[9] = new Image(); 
imgs[9].name = "Wulling";
imgs[9].src = "wulling.jpg"; 
imgs[9].year = "1892";
imgs[9].arch = "Allen Stem and Charles Reed";
imgs[9].description = "Built as Medical Hall; named Millard Hall in 1906. Fire damaged the building. It later became the site for the pharmacy building. Named for Frederick J. Wulling, first dean and founder of the College of Pharmacy.";


// Array with all loaded picture elements.
var loadedArray = new Array;  

var current = 0;
var timelength = -1;
var turnedOn = false;

//load pictures into new array
function loadPicturesIntoArray() 
{
	for(i = 0; i < imgs.length; ++i) 
    {
        var img = document.createElement("img"); //create an <img> element by using the document.createElement()
		img.src = imgs[i].src;
		img.setAttribute("class", "thumb");
		img.obj = imgs[i];
		img.onclick = function() 
        { 
            updatecurrent(this.obj); 
        };
		document.getElementById("thumbnails").appendChild(img);
		loadedArray.push(img); //push loaded image onto new array
	}
}

//set the first image to current
function startSlide() 
{
	loadedArray[current].setAttribute("id", "");
	current = 0;
	loadedArray[current].setAttribute("id", "current");
	document.getElementById("currentSlide").src = loadedArray[current].src;
	currentPictureText();
}

//Go to previous thumbnail
function previousSlide() 
{
	loadedArray[current].setAttribute("id", "");
	if(current == 0) current = loadedArray.length-1;
	else current--;
	loadedArray[current].setAttribute("id", "current");
	document.getElementById("currentslide").src = loadedArray[current].src;
	currentPictureText();
}

//increment the current image, wrapping in the case of max number of images
function nextSlide() 
{
	loadedArray[current].setAttribute("id", "");
	if(current == loadedArray.length-1) current = 0;
	else current++;
	loadedArray[current].setAttribute("id", "current");
	document.getElementById("currentSlide").src = loadedArray[current].src;
	currentPictureText();
}

// User pics from none, arch, year, or description.
function pickCategory() 
{
	var option = selectedInfo();
	dropDownSelection = option; 
	if(document.getElementById("current")) 
    { 
        currentPictureText(); 
    }
}

//start slide show. alert if already started. timed slideshow. 
function startSlides() 
{
	if(document.getElementById("current") == null) 
    {
        startImage(); 
    }
	if(turnedOn) 
    {
		alert("Slideshow is on.");
		return;
	}
	turnedOn = true;
	timelength = setInterval("nextSlide()", 1025);
}

// stop slide show
function stopSlides() 
{
	turnedOn = false;
	clearInterval(timelength);
}

//drop down selected info
function selectedInfo() 
{
	var select = document.getElementById("info_type");
	if(select.options.length > 0) 
    {
		return select.options[select.selectedIndex].value;
	}
	else return -1;
}

//info for current picture
function currentPictureText() 
{
	var text = document.getElementById("building_info");
	if(!text) 
    {
		text = document.createElement("text");
		text.id = "building_info";
		document.getElementById("info").appendChild(text);
	}
	
	text.innerHTML = "Image Information:<br/>Building: " + imgs[current].name + "<br/>"; 

	if(dropDownSelection == "Architect") 	
    { 
        text.innerHTML += "Architect: " + imgs[current].arch + "<br/>";         
    }
	else if (dropDownSelection == "Year")  
    { 
        text.innerHTML += "Year: " + imgs[current].year + "<br/>"; 
    }
	else if (dropDownSelection == "Description")  
    { 
        text.innerHTML += "Description: " + imgs[current].description + "<br/>"; 
    }
}
