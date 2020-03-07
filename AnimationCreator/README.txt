I wrote this program to allow for you to 
create new JSON files that include animations 
that you can later load in and add as an 
animation to your Animated Sprites.

Included within the "jsons/" folder is an example
JSON file created using this program. This example
corresponds to Link.png within the spritesheet 
folder.

A few pointers:
-The JSON files will always be created in the
"jsons/" folder. 

-In the beginning when it asks you if you want
to create/open an animation JSON. All
you need to do to open an already created
JSON, is place the JSON within the "jsons/" 
folder and then write the name when prompted.
From there you will be within that JSON file.
	-If you would like to edit an
	animation within the json, just use
	the same animation name and you'll
	be overwriting that animation with 
	new data.
	-To add new animations all that you
	need to do is simply give a new
	animation name. From there just set
	up the animation.

-Each animation consists of "frames", these
frames consist of the 4 corners that make up
the square surrounding the part of the 
spritesheet that makes up that frame. Keep 
these numbers in pixels. You can get the
pixels in a program like Photoshop or Paint.Net 
(free program found at: https://www.getpaint.net/).
In order to create a frame, you only need the 
Bottom Left corner and Top Right corner, all other
corners can be obtained from just those.

-When entering the "frame" as the program prompts,
make sure to enter it in the proper order.
The order is:
Bottom Left x,
Bottom Left y,
Top Right x,
Top Right y.

-MOST IMPORTANTLY:
Make sure to name your animations correctly. Later
when you're reading in the JSON file, you will need
the name of the animation in order to index the
JSON file.

Side note:
The project code for this is not... the cleanest.
This was written as a proof of concept program,
to show that a program for adding animations to
a JSON could work.

The actual goal is to maybe create a visual version
with ImGui that would allow for you to actually
press the corners of each frame and adjust the
corners. Could be a pretty cool tool?
 