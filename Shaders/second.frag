#version 450

layout(input_attachment_index = 0, binding = 0) uniform subpassInput inputColour; // Colour output from subpass 1
layout(input_attachment_index = 1, binding = 1) uniform subpassInput inputDepth;  // Depth output from subpass 1

layout(location = 0) out vec4 colour;

void main()
{
	float xHalf = 1366/2.0 ;
	if(gl_FragCoord.x > xHalf)
	{
		float lowerBound = 0.85;
		float upperBound = 1.0;
		
		float depth = subpassLoad(inputDepth).r;
		float depthColourScaled = 1.0f - ((depth - lowerBound) / (upperBound - lowerBound));
		colour = vec4(depthColourScaled, 0.0f, 0.0f, 1.0f);
	}
	else
	{
		colour = subpassLoad(inputColour).rgba;
	}
}