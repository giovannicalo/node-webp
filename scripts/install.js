const { promises: { mkdir } } = require("fs");
const { get } = require("https");
const { join } = require("path");

const { extract } = require("tar");

get(
	"https://chromium.googlesource.com/webm/libwebp/+archive/b0a860891dcd4c0c2d7c6149e5cccb6eb881cc21.tar.gz",
	async (response) => {
		const path = join(__dirname, "..", "libraries", "libwebp");
		await mkdir(path, { recursive: true });
		response.pipe(extract({ cwd: path }));
	}
);
