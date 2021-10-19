<template>
  <div>
    <nav
      class="navbar is-light is-fixed-top"
      role="navigation"
      aria-label="main navigation"
    >
      <div class="navbar-brand">
        <router-link :to="{ name: 'Home' }" class="navbar-item">
          <img
            src="../assets/images/logo.png"
            alt="Logo"
            style="max-width: 50px; margin-right: 10px"
          />
          Ezored
        </router-link>
      </div>
    </nav>

    <section class="section" style="text-align: center; margin-top: 50px">
      <div class="container">
        <h1 class="title">About</h1>

        <div class="columns is-mobile is-centered">
          <div class="column is-full">
            <img
              alt="Logo"
              src="../assets/images/logo.png"
              style="width: 100px"
            />
          </div>
        </div>

        <br />

        <div class="columns">
          <div class="column">
            <button class="button is-primary" v-on:click="back()">Back</button>
          </div>
        </div>
      </div>
    </section>
  </div>
</template>

<script>
export default {
  name: "About",
  props: {},
  data() {
    return {
      // ignore
    };
  },
  created: function () {
    // ignore
  },
  methods: {
    back() {
      this.$router.push({ name: "Home", params: {} });
    },
  },
};
</script>

<style scoped>
</style>
