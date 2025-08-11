declare module "fastfile" {
    interface FastFileHandler {
        write(buffer: Buffer, offset: number): Promise<void>;
        read(length: number, offset: number): Promise<Buffer>;
        close(): Promise<void>;
    }

    /**
     * Creates or overrides a file for writing.
     * @param path Path to the file to create or override.
     * @returns A handler for performing write/read and close operations.
     */
    export function createOverride(path: string): Promise<FastFileHandler>;

    /**
     * Opens an existing file for reading.
     * @param path Path to the existing file to read.
     * @returns A handler for performing read/write and close operations.
     */
    export function readExisting(path: string): Promise<FastFileHandler>;

    const fastFile: {
        createOverride(path: string): Promise<FastFileHandler>;
        readExisting(path: string): Promise<FastFileHandler>;
    };

    export default fastFile;
}
