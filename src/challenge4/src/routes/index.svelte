<script lang="ts">
import { gameState } from '$lib/scripts/gameManager';
import TicTacToeBoard from '$lib/views/TicTacToeBoard.svelte'
</script>


<style>
.container {
    display: grid;
    place-items: center;
    padding-top: 100px;
}
</style>


<div class="container">
    <TicTacToeBoard />
</div>

