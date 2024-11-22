uniform sampler2D texture;  // The text texture
uniform vec2 resolution;    // Resolution of the window
uniform vec3 glowColor;     // Color of the glow
uniform float glowRadius;   // Radius of the glow effect

void main() {
    vec2 uv = gl_TexCoord[0].xy;             // Normalized texture coordinates
    vec4 textColor = texture2D(texture, uv); // Sample the text texture

    // Initialize the glow effect
    float glow = 5.0;

    // Sample neighboring pixels with weighted contribution
    for (float x = -glowRadius; x <= glowRadius; x++) {
        for (float y = -glowRadius; y <= glowRadius; y++) {
            vec2 offset = vec2(x, y) / resolution;
            float weight = exp(-(x * x + y * y) / (2.0 * glowRadius * glowRadius)); // Gaussian weight
            vec4 sample = texture2D(texture, uv + offset);
            glow += sample.a * weight; // Accumulate weighted alpha values
        }
    }

    // Normalize the glow value
    glow /= (6.28318 * glowRadius * glowRadius); // Gaussian normalization factor

    // Apply glow color
    vec4 glowEffect = vec4(glowColor, 1.0) * glow;

    // Combine the text color with the glow effect
    gl_FragColor = textColor + glowEffect;
}
