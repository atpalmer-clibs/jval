#include <jval.h>
#include <string.h>

/*
 * Dummy API just to return newly allocated strings
 */
char *lookup_state(const char *city)
{
    if (strcmp(city, "New York") == 0)
        return strdup("New York");
    if (strcmp(city, "Chicago") == 0)
        return strdup("Illinois");
    return NULL;
}

int main(void)
{
    char *nyc_state = lookup_state("New York");  /* new string on heap */

    /* use jval_set* family of functions to set object properties */
    struct jval *nyc = jval_new_object();
    jval_set_string(nyc, "city", "New York");
    jval_set_string(nyc, "state", nyc_state);
    jval_set_long(nyc, "population", 8804190);

    char *chicago_state = lookup_state("Chicago");  /* new string on heap */

    struct jval *chicago = jval_new_object();
    jval_set_string(chicago, "city", "Chicago");
    jval_set(chicago, "state", jval_from_string(chicago_state));  /* same thing as above */
    jval_set_long(chicago, "population", 2746388);

    /*
     * we need to clean up these strings at some point.
     * we can do it now, and the jvals will still own a copy.
     * composite jvals will be entirely cleaned up with one jval_destroy,
     * but any raw c-strings we allocated have to be freed
     */
    free(nyc_state);
    free(chicago_state);

    /* we can nest objects within other objects
     * unlike jval_set_string, which copies c-strings,
     * jval_set steals jval refs, so
     * "nyc" and "chicago" should _not_ be freed separately */
    struct jval *locations = jval_new_object();
    jval_set(locations, "location", nyc);
    jval_set(locations, "location", chicago);  /* this is usually a bad idea, but
                                                * duplicate "keys" are legal */

    jval_out(locations, stdout);

    /* call jval_destroy on top-level jval only
     * nested jvals will be destroyed recursively */
    jval_destroy(locations);
}
