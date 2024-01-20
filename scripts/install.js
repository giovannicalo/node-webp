const { promises: { mkdir } } = require("fs");
const { get } = require("https");
const { join } = require("path");

const { extract } = require("tar");

get(
	"https://chromium.googlesource.com/webm/libwebp/+archive/ca332209cb5567c9b249c86788cb2dbf8847e760.tar.gz",
	async (response) => {
		const path = join(__dirname, "..", "libraries", "libwebp");
		await mkdir(path, { recursive: true });
		response.pipe(extract({ cwd: path }));
	}
);
