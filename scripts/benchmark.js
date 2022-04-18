const { readFileSync } = require("fs");
const { join } = require("path");

const { Format, decode, encode } = require("../source");

const iterations = 100;

const path = join(__dirname, "..", "test");

const webp = readFileSync(join(path, "512x512.webp"));

const rgba = {
	data: readFileSync(join(path, "512x512.rgba")),
	format: Format.rgba,
	height: 512,
	width: 512
};

const benchmark = async (label, method, ...parameters) => {
	const start = Date.now();
	for (let i = 0; i < iterations; i++) {
		await method(...parameters);
	}
	console.log(`${label}: ${((Date.now() - start) / iterations).toFixed(2)}ms`);
};

(async () => {
	for (const parameters of [
		["WebP => RGBA", decode, webp, Format.rgba],
		["WebP => YUV ", decode, webp, Format.yuv],
		["RGBA => WebP", encode, rgba, 90]
	]) {
		await benchmark(...parameters);
	}
})();
