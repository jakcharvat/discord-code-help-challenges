class GameManager {
    onloaded: Function | null
    managerInstance: any | null

    constructor(onloaded: Function | null = null) {
        this.onloaded = onloaded
        this.loadWasm()
    }

    async loadWasm() {
        const wasm = fetch('./gameManager.wasm')
        const { instance } = await WebAssembly.instantiateStreaming(wasm)
        this.managerInstance = instance
        this.onloaded && this.onloaded()
    }

    fib() {
        if (!this.managerInstance) {
            throw 'Not loaded yet'
        }

        return this.managerInstance.exports.fib()
    }
}


export default GameManager