package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"log"
	"net/http"
	"regexp"
	"encoding/json"
)

func SetMyCookie(response http.ResponseWriter){
	// Add a simplistic cookie to the response.
	cookie := http.Cookie{Name: "testcookiename", Value:"testcookievalue"}
	http.SetCookie(response, &cookie)
}

// Respond to URLs of the form /generic/...
func GenericHandler(response http.ResponseWriter, request *http.Request){

	// Set cookie and MIME type in the HTTP headers.
	SetMyCookie(response)
	response.Header().Set("Content-type", "text/plain")

	// Parse URL and POST data into the request.Form
	// err := request.ParseForm()
	// if err != nil {
	// 	http.Error(response, fmt.Sprintf("error parsing url %v", err), 500)
	// }

	// Send the text diagnostics to the client.
	fmt.Fprint(response,  "FooWebHandler says ... \n")
	// fmt.Fprintf(response, " request.Method     '%v'\n", request.Method)
	// fmt.Fprintf(response, " request.RequestURI '%v'\n", request.RequestURI)
	// fmt.Fprintf(response, " request.URL.Path   '%v'\n", request.URL.Path)
	// fmt.Fprintf(response, " request.Form       '%v'\n", request.Form)
	// fmt.Fprintf(response, " request.Cookies()  '%v'\n", request.Cookies())
}

// Respond to the URL /home with an html home page
func HomeHandler(response http.ResponseWriter, request *http.Request){
	response.Header().Set("Content-type", "text/html")
	webpage, err := ioutil.ReadFile("home.html")
	if err != nil { 
		http.Error(response, fmt.Sprintf("home.html file error %v", err), 500)
	}
	fmt.Fprint(response, string(webpage));
}

// Respond to URLs of the form /item/...
func ItemHandler(response http.ResponseWriter, request *http.Request){

	// Set cookie and MIME type in the HTTP headers.
	SetMyCookie(response)
	response.Header().Set("Content-type", "application/json")

	// Some sample data to be sent back to the client.
	data := map[string]string { "what" : "item", "name" : "" }

	// Was the URL of the form /item/name ?
	var itemURL = regexp.MustCompile(`^/item/(\w+)$`)
	var itemMatches = itemURL.FindStringSubmatch(request.URL.Path)
	// itemMatches is captured regex matches i.e. ["/item/which", "which"]
	if len(itemMatches) > 0 {
		// Yes, so send the JSON to the client.
		data["name"] = itemMatches[1] 
		json_bytes, _ := json.Marshal(data)
		fmt.Fprintf(response, "%s\n", json_bytes)

	} else {
		// No, so send "page not found."
		http.Error(response, "404 page not found", 404)
	}
}

func main(){
	port := 8000
	portstring := strconv.Itoa(port)

	// Register request handlers for two URL patterns.
	// (The docs are unclear on what a 'pattern' is, 
	// but seems be the start of the URL, ending in a /).
	// See gorilla/mux for a more powerful matching system.
	// Note that the "/" pattern matches all request URLs.
	mux := http.NewServeMux()
	mux.Handle("/home", http.HandlerFunc( HomeHandler ))
	mux.Handle("/item/", http.HandlerFunc( ItemHandler ))
	mux.Handle("/generic/", http.HandlerFunc( GenericHandler ))

	// Start listing on a given port with these routes on this server.
	// (I think the server name can be set here too , i.e. "foo.org:8080")
	log.Print("Listening on port " + portstring + " ... ")
	err := http.ListenAndServe(":" + portstring, mux)
	if err != nil {
		log.Fatal("ListenAndServe error: ", err)
	}
}