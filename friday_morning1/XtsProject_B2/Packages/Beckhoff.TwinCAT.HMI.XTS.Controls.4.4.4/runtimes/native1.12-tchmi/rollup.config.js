import { terser } from 'rollup-plugin-terser';

export default [
    {
        input:  './XTS/Controls/XtsView/bin/TcXtsHmiView.js',
        output: {
            file: './XTS/Controls/XtsView/bin/TcXtsHmiView.js',
            format: 'es',
            sourcemap: false
        },
        plugins: [
            terser({
                module: true,
                keep_fnames: false,
                toplevel: true,
                mangle: {
                    reserved: ['TcHmi', 'XTS', 'Controls', 'XtsView'],
                }
            })
        ]
    }
]