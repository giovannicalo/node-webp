const { promises: { mkdir } } = require("fs");
const { get } = require("https");
const { join } = require("path");

const { extract } = require("tar");

get(
	"https://chromium.googlesource.com/webm/libwebp/+archive/b557776962a3dcc985d83bd4ed94e1e2e50d0fa2.tar.gz",
	async (response) => {
		const path = join(__dirname, "..", "libraries", "libwebp");
		await mkdir(path, { recursive: true });
		response.pipe(extract({ cwd: path }));
	}
);
