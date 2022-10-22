const { readFileSync } = require("fs");
const { join } = require("path");

const { Format, decode } = require(".");

const path = join(__dirname, "..", "test");

const rgba511 = readFileSync(join(path, "511x511.rgba"));

const rgba512 = readFileSync(join(path, "512x512.rgba"));

const webp511 = readFileSync(join(path, "511x511.webp"));

const webp512 = readFileSync(join(path, "512x512.webp"));

const yuv511 = readFileSync(join(path, "511x511.yuv"));

const yuv512 = readFileSync(join(path, "512x512.yuv"));

it("should decode an even-sized WebP as RGBA", async () => {
	const decoded = await decode(webp512, Format.rgba);
	expect(Buffer.from(decoded.data).equals(rgba512)).toBeTruthy();
	expect(decoded.format).toBe(Format.rgba);
	expect(decoded.height).toBe(512);
	expect(decoded.width).toBe(512);
});

it("should decode an odd-sized WebP as RGBA", async () => {
	const decoded = await decode(webp511, Format.rgba);
	expect(Buffer.from(decoded.data).equals(rgba511)).toBeTruthy();
	expect(decoded.format).toBe(Format.rgba);
	expect(decoded.height).toBe(511);
	expect(decoded.width).toBe(511);
});

it("should decode an even-sized WebP as YUV", async () => {
	const decoded = await decode(webp512, Format.yuv);
	expect(Buffer.from(decoded.data).equals(yuv512)).toBeTruthy();
	expect(decoded.format).toBe(Format.yuv);
	expect(decoded.height).toBe(512);
	expect(decoded.width).toBe(512);
});

it("should decode an odd-sized WebP as YUV", async () => {
	const decoded = await decode(webp511, Format.yuv);
	expect(Buffer.from(decoded.data).equals(yuv511)).toBeTruthy();
	expect(decoded.format).toBe(Format.yuv);
	expect(decoded.height).toBe(512);
	expect(decoded.width).toBe(512);
});

it("should throw when given no arguments", () => {
	expect(() => {
		decode();
	}).toThrow("[nodeWebp::decode] At least one argument is required");
});

it("should throw when the first argument is not a buffer", () => {
	expect(() => {
		decode(42);
	}).toThrow("[nodeWebp::decode] Argument is not a buffer");
});

it("should throw when given a buffer that isn't a WebP", async () => {
	await expect(
		decode(Buffer.from([1, 2, 3]))
	).rejects.toThrow("[nodeWebp::Decoder::Execute] Failed to read header");
});

it("should throw when given a format that isn't RGBA or YUV", async () => {
	await expect(
		decode(webp512, 42)
	).rejects.toThrow("[nodeWebp::Decoder::Execute] Format is invalid");
});

it("shouldn't throw when given more than two arguments", () => {
	expect(() => {
		decode(webp512, Format.rgba, 42);
	}).not.toThrow();
});
