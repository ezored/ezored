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
        <h1 class="title">Ezored</h1>

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
            <router-link
              :to="{ name: 'ToDo' }"
              tag="button"
              class="button is-primary"
            >
              ToDo
            </router-link>
          </div>
          <div class="column">
            <router-link
              :to="{ name: 'About' }"
              tag="button"
              class="button is-warning"
            >
              About
            </router-link>
          </div>
        </div>

        <div
          v-if="message"
          class="columns is-mobile is-centered"
          style="margin-top: 30px; margin-bottom: 30px"
        >
          <div class="column is-full">
            <article class="message is-info">
              <div class="message-body">
                {{ message }}
              </div>
            </article>
          </div>
        </div>
      </div>
    </section>
  </div>
</template>

<script>
export default {
  name: "Home",
  props: {},
  data() {
    return {
      message: "",
    };
  },
  created: function () {
    // ignore
  },
  methods: {
    // ignore
  },
};
</script>

<style scoped>
</style>
