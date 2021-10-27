# Node WebP

[![Build Status](https://github.com/giovannicalo/node-webp/actions/workflows/build.yml/badge.svg)](https://github.com/giovannicalo/node-webp/actions/workflows/build.yml)
[![Coverage Status](https://coveralls.io/repos/github/giovannicalo/node-webp/badge.svg)](https://coveralls.io/github/giovannicalo/node-webp)

## Prerequisites

* [CMake](https://cmake.org) >= 3.21.0

## Installation

```bash
npm install giovannicalo/node-webp
```

> Not yet published to NPM. This will install it from GitHub.

## Usage

### Decoding

```javascript
const { promises: { readFile, writeFile } } = require("fs");

const { Format, decode } = require("webp");

(async () => {
    const webp = await readFile("foo.webp");
    const rgba = await decode(webp, Format.rgba);
    console.log(rgba);
    // {
    //   data: Uint8ClampedArray(8294400) [...],
    //   format: 0,
    //   height: 1080,
    //   width: 1920
    // }
    await writeFile("foo.rgba", rgba.data);
    const yuv = await decode(webp, Format.yuv);
    console.log(yuv);
    // {
    //   data: Uint8ClampedArray(3110400) [...],
    //   format: 1,
    //   height: 1080,
    //   width: 1920
    // }
    await writeFile("foo.yuv", yuv.data);
})();
```

### Encoding

```javascript
const { promises: { readFile, writeFile } } = require("fs");

const { Format, encode } = require("webp");

(async () => {
    const rgba = {
        data: await readFile("foo.rgba"),
        format: Format.rgba,
        height: 1080,
        width: 1920
    };
    const webp = await encode(rgba, 90);
    console.log(webp);
    // <Buffer ...>
    await writeFile("foo.webp", webp);
})();
```

## API

### `Format.rgba`

Value: 0

Standard RGBA format, supports both decoding and encoding.

### `Format.yuv`

Value: 1

YUV I420 format, currently supports only decoding. Smaller and faster than RGBA, but less straightforward. When decoding, if the source WebP has odd dimensions, they will be rounded up to the nearest even number.

### `decode(data: Buffer, format = Format.rgba): Promise<Image>`

Decodes the WebP image stored in the `data` buffer as `format`, which can be either `Format.rgba` or `Format.yuv`.

Returns a promise resolving to an object with `data`, `height`, `format` and `width` properties.

### `encode(image: Image, quality = 90): Promise<Buffer>`

Encodes a raw `image` as WebP with the given `quality`. `image` must be an object with `data`, `height`, `format` and `width` properties. `image.format` currently has to be `Format.rgba`.

Returns a promise resolving to a buffer.
