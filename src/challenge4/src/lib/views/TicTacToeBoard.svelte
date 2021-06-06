<script lang="ts">
import type { WinInfo } from '$lib/scripts/gameManager'
import { gameState, winDirectionClass } from '$lib/scripts/gameManager';
import TicTacToeBox from '$lib/views/TicTacToeBox.svelte'

const getWinClass = (win: WinInfo): string => {
    const direction = winDirectionClass(win.direction)
    const row = `win-row-${win.winningRow}`
    const col = `win-col-${win.winningCol}`
    return `win ${direction} ${row} ${col}`
}

let winClass: string = ''

gameState.subscribe(state => {
    const win = state.win
    if (win) {
        winClass = getWinClass(win)
    } else {
        winClass = ''
    }
})
</script>


<style>
#grid {
    --grid-gap: 8px;
    --box-size: 100px;

    --win-line-length: 300px;
    --win-line-breadth: 20px;
    --win-line-background: #13271e;

    --center-in-box: calc(var(--box-size) / 2);
    --skip-box: calc(var(--box-size) + var(--grid-gap));

    display: grid;
    grid-template-columns: repeat(3, max-content);
    gap: var(--grid-gap);
    position: relative;
}

#grid.win::before { 
    --rotate: 0deg;
    content: '';
    background: var(--win-line-background);
    position: absolute;
    z-index: 10;
    transform: translate(-50%, -50%) rotate(var(--rotate));
    width: var(--win-line-length);
    height: var(--win-line-breadth);
}

#grid.win-horizontal::before {
    left: 50%;
}

#grid.win-horizontal.win-row-0::before {
    top: var(--center-in-box);
}
#grid.win-horizontal.win-row-1::before {
    top: calc(var(--skip-box) + var(--center-in-box));
}
#grid.win-horizontal.win-row-2::before {
    top: calc(var(--skip-box)*2 + var(--center-in-box));
}


#grid.win-vertical::before {
    --rotate: 90deg;
    top: 50%;
}

#grid.win-vertical.win-col-0::before {
    left: var(--center-in-box);
}
#grid.win-vertical.win-col-1::before {
    left: calc(var(--skip-box) + var(--center-in-box));
}
#grid.win-vertical.win-col-2::before {
    left: calc(var(--skip-box)*2 + var(--center-in-box));
}


#grid.win-diagonal::before {
    --win-line-length: 360px;
    --win-line-breadth: 15px;
    left: 50%;
    top: 50%;
}

#grid.win-diagonal-forward::before {
    --rotate: -45deg;
}

#grid.win-diagonal-back::before {
    --rotate: 45deg;
}
</style>


<div id="grid" class={winClass}>
    {#each [0, 1, 2] as row}
        {#each [0, 1, 2] as col}
            <TicTacToeBox row={row} col={col} />
        {/each}
    {/each}
</div>
