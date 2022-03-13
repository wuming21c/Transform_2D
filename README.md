# repo purpose

Practice on 2D image transformation

# program function
Draw a rectangle, and calculat its 2D transformations.

# Method/Steps:
1. Open an empty window/"canvas"
2. Create a rectange with customized size
3. Calculate the vertices after transformations: translation, rigid, similarity, affine, or perspective.

# Thought
OpenCV

Trackbar to customize the rectangle size

Manually set the transformation parameters in the code.

'Manually' calculate the transform using maxtrix multiplification. (does not use OpenCV function on Mat, using Eigen package.)

# Note
Practice inspired from Ex. 2.2, "Computer Vision: Algorithm and Appliations", Szeliski. But with less function: mouse dragging. There is no interaction on the screen in this program.
