<style>
:global(:root) {
    --primary-colour: #68dba3;
    --shadow-colour: #3faf79;
    --cross-colour: #1e6b46;
}

:global(h1) {
    font-family: 'Recursive', sans-serif;
    font-size: 2.5rem;
    --casl: 'CASL' 0.1;
    --wght: 'wght' 800;
    font-variation-settings: var(--casl), var(--wght);
    margin: 20px;
}
</style>


<slot />