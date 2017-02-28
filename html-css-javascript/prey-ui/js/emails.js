function setupLeftPane()
{
	//from http://stackoverflow.com/a/36610490
	let child = document.getElementById("emailListWrapper");
	let addWidth = child.offsetWidth - child.clientWidth + "px";
	child.style.width = "calc(100% + " + addWidth + ")";
}
