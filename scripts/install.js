const { promises: { mkdir } } = require("fs");
const { get } = require("https");
const { join } = require("path");

const { extract } = require("tar");

get(
	"https://chromium.googlesource.com/webm/libwebp/+archive/fedac6cc69cda3e9e04b780d324cf03921fb3ff4.tar.gz",
	async (response) => {
		const path = join(__dirname, "..", "libraries", "libwebp");
		await mkdir(path, { recursive: true });
		response.pipe(extract({ cwd: path }));
	}
);
