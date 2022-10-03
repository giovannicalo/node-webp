const { promises: { mkdir } } = require("fs");
const { get } = require("https");
const { join } = require("path");

const { extract } = require("tar");

get(
	"https://chromium.googlesource.com/webm/libwebp/+archive/0d1f12546bd803099a60c070517a552483f3790e.tar.gz",
	async (response) => {
		const path = join(__dirname, "..", "libraries", "libwebp");
		await mkdir(path, { recursive: true });
		response.pipe(extract({ cwd: path }));
	}
);
