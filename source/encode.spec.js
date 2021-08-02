const { readFileSync } = require("fs");
const { join } = require("path");

const { Format, encode } = require(".");

const path = join(__dirname, "..", "test");

const riffMagicNumber = Buffer.from([0x52, 0x49, 0x46, 0x46]);

const webpMagicNumber = Buffer.from([0x57, 0x45, 0x42, 0x50]);

const rgba511 = {
	data: readFileSync(join(path, "511x511.rgba")),
	format: Format.rgba,
	height: 511,
	width: 511
};

const rgba512 = {
	data: readFileSync(join(path, "512x512.rgba")),
	format: Format.rgba,
	height: 512,
	width: 512
};

it("should encode an even-sized RGBA image as WebP", async () => {
	const webp = await encode(rgba512, 90);
	expect(webp.slice(0, 4).equals(riffMagicNumber)).toBeTruthy();
	expect(webp.slice(8, 12).equals(webpMagicNumber)).toBeTruthy();
});

it("should encode an odd-sized RGBA image as WebP", async () => {
	const webp = await encode(rgba511, 90);
	expect(webp.slice(0, 4).equals(riffMagicNumber)).toBeTruthy();
	expect(webp.slice(8, 12).equals(webpMagicNumber)).toBeTruthy();
});

it("should throw when given no arguments", () => {
	expect(() => {
		encode();
	}).toThrow();
});

it("should throw when the first argument is not an object", () => {
	expect(() => {
		encode(42);
	}).toThrow();
});

it("shouldn't throw when given more than two arguments", () => {
	expect(() => {
		encode(rgba512, 90, 42);
	}).not.toThrow();
});
